import re

BUNDLE_SPEC = "bundle.txt"
OUTPUT_FILE = "acro.hpp"

def load_module(name, path):
    output_lines = []
    output_lines.append(f"#ifdef ACRO_FEATURE_{name}")

    with open(path, "r") as module:
        for line in module:
            line = line[:-1]

            if line.strip().startswith("//!"):
                # control comment
                act = line.split("[")[1].split("]")[0]

                if act == "SOURCE":
                    output_lines.append("#ifdef ACRO_IMPL")
                    
                    source_path = line.split("]")[1].strip()

                    with open(source_path, "r") as source:
                        for line in source:
                                # stop a module's source from including its own header file
                            include_rx = r'#include\s*["<](.*?)[">]'
                            matches = re.findall(include_rx, line)

                            if len(matches) > 0:
                                included_path = matches[0]
                                if "./include/" + included_path == path:
                                   continue

                            output_lines.append(line[:-1])

                    output_lines.append("#endif")
                    continue
            output_lines.append(line)

    output_lines.append(f"#endif")

    return output_lines

def main():
    output_lines = []

    with open(BUNDLE_SPEC, "r") as bundle:
        module_step = 0
        module_name = ""

        i = 0
        for line in bundle:
            i += 1
            line = line.strip()
            if len(line) == 0 or line[0] == '/':
                if module_step != 0:
                    print(f"Incomplete module specification for {module_name}")
                continue
            
            if module_step == 1 and (line[0] != '.' or len(line) < 2):
                print(f"Incomplete module path for {module_name}")

            if module_step == 1:        
                module_path = line.strip()
                print(f"Loading module {module_name} from {module_path}")
                output_lines += load_module(module_name, module_path)
                module_step = 0
                continue

            if module_step == 0 and line[0] == '.':
                if len(line) < 2 or line[1:].isspace():
                    print(f"Unnamed module on line {i}")
                module_name = line[1:].replace(" ", "")
                module_step = 1
                
            if line[0] == '!' and len(line) > 1:
                output_lines.append(line[1:])

    
    output_str = "\n".join(output_lines)

    with open(OUTPUT_FILE, "w") as output:
        output.write(output_str)
if __name__ == '__main__':
    main()
