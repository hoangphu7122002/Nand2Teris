import Command

class ArithmeticTranslate():
    OPERATION_INSTRUCTION = {
        'add' : 'M=M+D',
        'sub' : 'M=M-D',
        'neg' : 'M=-M',
        'or' : 'M=M|D',
        'not' : 'M=!M',
        'and' : 'M=M&D'
    }
    
    COMP_COMMAND = {
        'eq' : {'jump' : 'JNE'},
        'lt': {'jump' : 'JLE'},
        'gt': {'jump' : 'JGE'}
    }
    
    def __init__(self):
        self.comp_counters = {
            'eq' : {'count' : 0},
            'lt' : {'count' : 0},
            'gt' : {'count' : 0}
        }
        
    def translate(self,command):
        if command.text in self.COMP_COMMAND:
            return self.comp_translate(command)
        else:
            return self.arithmetic_translate(command)
    
    def arithmetic_translate(self,command_text):
        if command_text in ['add','sub','and','or']:
            #binary operation
            return 
        else:
            #unary operation
            return 
            
    #i do not understand
    def comp_translate(self,command_text):
        counter = self.comp_counters[command_text]
        counter['count'] += 1
        label_identity = '{}{}'.format(command_text.upper(),counter['count'])
        
        jump = self.COMP_COMMAND[command_text]['jump']
        
        
        