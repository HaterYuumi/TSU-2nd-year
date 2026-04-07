import heapq
from collections import defaultdict
import math

class ArithmeticCompressor:
    def __init__(self, precision=32):
        self.precision = precision
        self.one = 1 << self.precision
        self.half = self.one >> 1
        self.quarter = self.half >> 1
        self.three_quarters = self.half + self.quarter
        
    def calculate_cumulative_freq(self, frequency):
        total = sum(frequency.values())
        cum_freq = {}
        cumulative = 0
        
        for char, freq in sorted(frequency.items()):
            cum_freq[char] = (cumulative, cumulative + freq)
            cumulative += freq
        
        return cum_freq, total
    
    def encode(self, text, frequency):
        cum_freq, total = self.calculate_cumulative_freq(frequency)
        
        low = 0
        high = self.one - 1
        pending_bits = 0
        encoded_bits = []
        
        for char in text:
            if char not in cum_freq:
                raise ValueError(f"Символ '{char}' не найден в таблице частот")
                
            char_low, char_high = cum_freq[char]
            
            range_size = high - low + 1
            new_low = low + (range_size * char_low) // total
            new_high = low + (range_size * char_high) // total - 1
            
            low, high = new_low, new_high
            
            while True:
                if high < self.half:
                    encoded_bits.append('0')
                    encoded_bits.extend(['1'] * pending_bits)
                    pending_bits = 0
                elif low >= self.half:
                    encoded_bits.append('1')
                    encoded_bits.extend(['0'] * pending_bits)
                    pending_bits = 0
                    low -= self.half
                    high -= self.half
                elif low >= self.quarter and high < self.three_quarters:
                    pending_bits += 1
                    low -= self.quarter
                    high -= self.quarter
                else:
                    break
                    
                low <<= 1
                high = (high << 1) | 1
        
        pending_bits += 1
        if low < self.quarter:
            encoded_bits.append('0')
            encoded_bits.extend(['1'] * pending_bits)
        else:
            encoded_bits.append('1')
            encoded_bits.extend(['0'] * pending_bits)
        
        binary_str = ''.join(encoded_bits)
        byte_array = bytearray()
        for i in range(0, len(binary_str), 8):
            byte = binary_str[i:i+8].ljust(8, '0')
            byte_array.append(int(byte, 2))
        
        return byte_array, cum_freq, total
    
    def decode(self, encoded_bytes, cum_freq, total, original_length):
        binary_str = ''.join(f'{byte:08b}' for byte in encoded_bytes)
        
        low = 0
        high = self.one - 1
        value = 0
        
        for i in range(self.precision):
            if i < len(binary_str):
                value = (value << 1) | int(binary_str[i])
            else:
                value <<= 1
        
        decoded_text = []
        bit_index = self.precision
        
        for _ in range(original_length):
            range_size = high - low + 1
            scaled_value = ((value - low + 1) * total - 1) // range_size
            
            char_found = None
            for char, (char_low, char_high) in cum_freq.items():
                if char_low <= scaled_value < char_high:
                    char_found = char
                    break
            
            if char_found is None:
                raise ValueError("Не удалось найти символ для декодирования")
            
            decoded_text.append(char_found)
            
            char_low, char_high = cum_freq[char_found]
            new_low = low + (range_size * char_low) // total
            new_high = low + (range_size * char_high) // total - 1
            
            low, high = new_low, new_high
            
            while True:
                if high < self.half:
                    pass
                elif low >= self.half:
                    value -= self.half
                    low -= self.half
                    high -= self.half
                elif low >= self.quarter and high < self.three_quarters:
                    value -= self.quarter
                    low -= self.quarter
                    high -= self.quarter
                else:
                    break
                    
                low <<= 1
                high = (high << 1) | 1
                value = (value << 1) | (int(binary_str[bit_index]) if bit_index < len(binary_str) else 0)
                bit_index += 1
        
        return ''.join(decoded_text)

def console():
    choice = input("Что вы хотите сделать? Введите 0 для кодирования или 1 для декодирования: ")
    if choice not in ['0', '1']:
        print("Неверный ввод! Пожалуйста, введите 0 или 1.")
        return console()

    input_file_path = 'text.txt'
    
    if choice == '0':
        output_file_path = 'encoded_arithmetic.bin'

        with open(input_file_path, 'r', encoding='utf-8') as file:
            text = file.read()

        frequency = defaultdict(int)
        for char in text:
            frequency[char] += 1

        compressor = ArithmeticCompressor()
        encoded_text, cum_freq, total = compressor.encode(text, frequency)

        with open(output_file_path, 'wb') as file:
            file.write(len(text).to_bytes(4, 'big'))
            
            file.write(total.to_bytes(4, 'big'))
            
            file.write(len(frequency).to_bytes(2, 'big'))
            for char, freq in frequency.items():
                char_bytes = char.encode('utf-8')
                file.write(len(char_bytes).to_bytes(1, 'big'))
                file.write(char_bytes)
                file.write(freq.to_bytes(4, 'big'))
            
            file.write(len(encoded_text).to_bytes(4, 'big'))
            file.write(encoded_text)

        original_size = len(text.encode('utf-8'))
        encoded_size = len(encoded_text) + 4 + 4 + 2 + (len(frequency) * (1 + 4)) + 4  

        print("\nАрифметическое сжатие завершено!")
        print("Размер исходного текста:", original_size, "байт")
        print("Размер закодированного текста:", encoded_size, "байт")
        print("Коэффициент сжатия:", f"{encoded_size/original_size:.2%}")

    elif choice == '1':
        output_file_path = 'decoded_arithmetic.txt'

        with open('encoded_arithmetic.bin', 'rb') as file:
            original_length = int.from_bytes(file.read(4), 'big')
            
            total = int.from_bytes(file.read(4), 'big')
            
            freq_count = int.from_bytes(file.read(2), 'big')
            frequency = {}
            for _ in range(freq_count):
                char_len = int.from_bytes(file.read(1), 'big')
                char = file.read(char_len).decode('utf-8')
                freq = int.from_bytes(file.read(4), 'big')
                frequency[char] = freq
            
            encoded_len = int.from_bytes(file.read(4), 'big')
            encoded_text = file.read(encoded_len)

        compressor = ArithmeticCompressor()
        cum_freq, _ = compressor.calculate_cumulative_freq(frequency)
        decoded_text = compressor.decode(encoded_text, cum_freq, total, original_length)

        with open(output_file_path, 'w', encoding='utf-8') as f:
            f.write(decoded_text)

        print("\nДекодированный текст:")
        print(decoded_text[:200] + "..." if len(decoded_text) > 200 else decoded_text)

if __name__ == "__main__":
    console()
