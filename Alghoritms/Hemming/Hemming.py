class Hemming:
    def __init__(self,message,*,BITS = 16):
        self.BITS = BITS # бит на букву
        self.ECC = self.__get_power_of_two(self.BITS) # степень двойки
        self.message = message

    def __get_binary(self,ch):
        '''
        Данная функция кодирует букву из кодировки ASCII в двоичную систему счисления.

        Функция дополняет результат до указанного в объекте количество бит.

        :param ch: буква , которую необходимо кодировать
        :return: закодированная буква в двоичной системе счисления
        '''
        return bin(ord(ch))[2:].zfill(self.BITS)

    def __get_power_of_two(self,number):
        '''
                Данная функция возвращает минимальную степень числа 2 , по входному числу

                :param number: число, для которого нужно получить степень
                :return: степень двойки
        '''
        power = 1
        while 2**power < number:
            power += 1
        return power

    def to_hemming_code(self):
        '''
        Данная функция кодирует сообщение с помощью алгоритма Хэмминга

        :return: закодированное сообщение
        '''
        result = ""
        for ch in self.message:
            codes = [self.__get_binary(x) for x in ch]
            main_code = list(map(int, ''.join(x for x in codes)))
            main_code = self.__insert_control_bit(main_code)
            ecc_value = self.__calculate_control_bit(main_code)
            for n in range(self.ECC + 1):
                main_code[2 ** n - 1] = ecc_value[n]
            result += ''.join(str(x) for x in main_code)
        return result

    def __insert_control_bit(self,main_code):
        '''
        Данная функция вставляет в сообщение контрольные биты в виде нулей

        :param main_code: сообщение
        :return: сообщение с контрольными битами
        '''
        for n in range(self.ECC+1):
            if 2**n <= len(main_code):
               main_code.insert(2**n-1,0)
        return main_code

    def __get_positions(self,len_main_code,n):
        '''
        Данная функция возвращает список позиций которые нужно посетить

        Например: есть интервал 2 , длина сообщение - 6

        Тогда позиции будут следующими : [0,1,4,5]

        :param len_main_code: длина сообщения
        :param n: интервал и количество позиций
        :return:
        '''
        pos = []
        index = n
        y = 0
        while index <= len_main_code:
            pos.append(index)
            y += 1
            index += 1
            if y == n:
                index += n
                y = 0
        return pos

    def __calculate_control_bit(self,main_code):
        '''
        Данная функция вычисляет контрольные биты для сообщения

        :param main_code: сообщение
        :return: список контрольных бит
        '''
        ecc_value = []
        len_main_code = len(main_code)
        for n in range(self.ECC+1):
            ECC_POSITIONS = self.__get_positions(len_main_code,2**n)
            y = 0
            for x in ECC_POSITIONS:
                if main_code[x-1] == 1:
                    y += 1
            ecc_value.append(y % 2)
        return ecc_value

    def __get_ecc_error_bits(self,main_code):
        '''
        Данная функция возвращает контрольные биты для сообщения , где контрольные биты = 0

        :param main_code: сообщение
        :return: список контрольных бит в которых есть ошибки
        '''
        _this_code = list(main_code)
        for n in range(self.ECC + 1):
            _this_code[2 ** n - 1] = 0
        return self.__calculate_control_bit(_this_code)

    def __get_error_position(self,main_code):
        '''
        Данная функция возвращает позицию в которой находится ошибка

        :param main_code: сообщение
        :return: индекс позиции с ошибкой
        '''
        ecc_value = self.__get_ecc_error_bits(main_code)
        amount = -1
        for x in self.__checker(main_code, ecc_value):
            amount += 2**x
        return amount

    def __checker(self,main_code, ecc_value):
        '''
        Данная функция возращает список контрольных бит с ошибкой

        :param main_code: сообщение
        :param ecc_value: новые контрольные биты
        :return: списоок контрольных бит с ошибкой
        '''
        ecc_old = []
        for n in range(self.ECC+1):
            ecc_old.append(main_code[2**n-1])
        error_list = []
        for i,x in enumerate(ecc_old):
            if ecc_value[i] != x:
                error_list.append(i)
        return error_list

    def __is_bool(self,variable) -> bool:
        '''
        Данная функция проверяет сообщение на двоичную систему счисления

        :param variable: сообщение
        :return: True or False
        '''
        new_bool = [x for x in variable if x in ["0", "1"]]
        return len(variable) == len(new_bool)

    def from_hemming_code(self,main_code):
        '''
        Данная функция возвращает декодированное сообщение алгоритмом Хэмминга

        :param main_code: закодированное сообщение
        :return: декодированное сообщение
        '''
        if len(main_code) % (self.BITS + self.ECC+1) != 0:
            raise Exception(f"Количество разрядов в букве не равно {self.BITS}!")
        if not self.__is_bool(main_code):
            raise Exception("Число не двоичное")
        if len(main_code) == 0:
            raise Exception("Передана пустая строка!")
        chars = [main_code[x:x+self.BITS+ self.ECC+1] for x in range (0, len(main_code), self.BITS+ self.ECC+1)]
        result = ""
        for ch in chars:
            main_code = list(map(int,ch))
            error_position = self.__get_error_position(main_code)
            if error_position != -1:
                if main_code[error_position] == 0:
                    main_code[error_position] = 1
                else:
                    main_code[error_position] = 0

            for n in range(self.ECC,-1,-1):
                if 2**n <= len(main_code):
                   main_code.pop(2**n-1)
            while(main_code[0] == 0):
                main_code.pop(0)
            result += chr(int('0b' + ''.join(str(x) for x in main_code),2))
        return result

    def find_errors_message(self,message):
        '''
        Данная функция создана для графического интерфейса
        Возвращает информацию об ошибках в виде HTML кода

        :param message: кодированное сообщение
        :return: информация об ошибках HTML
        '''
        if len(message) % (self.BITS + self.ECC+1) != 0:
            raise Exception(f"Количество разрядов в букве не равно {self.BITS}!")
        if not self.__is_bool(message):
            raise Exception("Число не двоичное")
        if len(message) == 0:
            raise Exception("Передана пустая строка!")
        chars = [message[x:x + self.BITS + self.ECC + 1] for x in range(0, len(message), self.BITS + self.ECC + 1)]
        result = ""
        for i,ch in enumerate(chars,start=1):
            result += f"<div align='center'><b>Буква №{i}</b></div><br>"
            main_code = list(map(int, ch))
            ecc_value = self.__get_ecc_error_bits(main_code)
            errors = self.__checker(main_code, ecc_value)
            if len(errors) == 0:
                result += "<b style='color:Green;'>Ошибок нет!</b>"
                continue
            for error in errors:
                result += f"Неверный <b style='color:Tomato;'>{2**error}-ый</b> контрольный бит<br>"
            amount = 0
            for x in errors:
                amount += 2 ** x
            result += f"Ошибка в <b style='color:Tomato;'>{amount}-ом</b> бите <br>"
        return result

if __name__ == "__main__":
    text = input("Input text: ")
    hem = Hemming(text,BITS=8)
    print(f"Encode = {hem.to_hemming_code()}")

    encode_text = input("Input encode text : ")
    from_hemm = hem.from_hemming_code(encode_text)
    print(f"Decode = {from_hemm}")