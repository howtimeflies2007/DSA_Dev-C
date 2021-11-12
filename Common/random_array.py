# -*- coding: UTF-8 -*- 

import sys
import numpy as np

low  = int(sys.argv[1])
high = int(sys.argv[2])
size = int(sys.argv[3])

print('low: {}'.format(str(low)))
print('high: {}'.format(str(high)))
print('size: {}'.format(str(size)))

random_int = np.random.randint(high)

print('random_int: {}'.format(str(random_int)))

random_int_list = np.random.randint(low, high, size).tolist()

random_str_txt = map(lambda x:str(x) + '\n', random_int_list)

f_input_txt = open('input.txt', 'w')
f_input_txt.writelines(random_str_txt)

random_str_h = map(lambda x:str(x), random_int_list)

file_head = '#ifndef _INPUT_H_\n#define _INPUT_H_\n\n'
random_var_positive = 'int random_positive_int = {};\n'.format(str(random_int))
random_var_negative = 'int random_negative_int = {};\n\n'.format(str(0 - random_int))
size_var = 'int input_size = {};\n'.format(str(size))
array_head = 'int input_array[{}] = {{\n'.format(str(size))
array_elements = ',\n'.join(random_str_h)
array_tail = '};\n\n'
file_tail = '#endif\n'

f_input_h = open('input.h', 'w')
f_input_h.writelines(file_head + random_var_positive + random_var_negative + size_var + array_head + array_elements + array_tail + file_tail)

extern_head = '#ifndef _EXTERN_INPUT_H_\n#define _EXTERN_INPUT_H_\n\n'
extern_body = 'extern int random_positive_int;\n' + 'extern int random_negative_int;\n' + 'extern int input_size;\n' + 'extern int input_array[{}];\n\n'.format(str(size))
extern_tail = '#endif\n'

f_extern_input_h = open('extern_input.h', 'w')
f_extern_input_h.writelines(extern_head + extern_body + extern_tail)

