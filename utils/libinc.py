def include(lib, out, placeholder):
    return out.replace(placeholder, lib)

def remove_tests(code):
    import re
    return re.sub(r'#ifndef\ TESTS(.|\s)*?#endif\s*', '', code)

if __name__ == '__main__':
    import os
    import sys

    library_name = sys.argv[2]
    library_path = os.path.expanduser('~/dev/competitive/lib/')
    input_file = sys.argv[1]

    with open(library_path + library_name + '.cpp', 'r') as libfile:
        library = libfile.read()

    with open(input_file, 'r') as clientcodefile:
        clientcode = clientcodefile.read()

    clientcode = include(library, clientcode, '[' + library_name + ']')
    clientcode = remove_tests(clientcode)

    with open(input_file, 'w') as clientcodefile:
        clientcodefile.write(clientcode)
