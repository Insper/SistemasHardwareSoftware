from grading_tools import TestConfiguration, ProgramTest, CheckOutputMixin
import sys

class TesteLabC(ProgramTest, CheckOutputMixin):
    pass


if __name__ == "__main__":
    if len(sys.argv) < 2: 
        print('Uso: corretor.py seu_programa_compilado')
        sys.exit(-1)
        
    tests = TestConfiguration.from_pattern('.', 'in*.txt', 'out*txt')
    tester = TesteLabC(sys.argv[1], tests)
    tester.main()
    