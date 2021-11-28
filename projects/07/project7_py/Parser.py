import Command

class Parser():
    
    def __init__(self,input_file):
        self.input_file = open(input_file, 'r')
        self.has_command = True
        self.cur_command = None
        self.next_command = None
    
    def has_valid_command(self):
        return not self.cur_command.isWhiteSpace() and not self.cur_command.isComment()
    
    #access next element
    def advance(self):
        self.__update__cur_command()
        self.__update_next_command()
        self.__update__has_command()
    
    def __update__has_command(self):
        if self.next_command.isEMPTY():
            self.has_command = False
    
    def __update__cur_command(self):
        if self.cur_command is None:
            txt = self.input_file.readline()
            self.cur_command = Command(txt)
        else:
            self.cur_command = self.next_command
    
    def __update_next_command(self):
        text = self.input_file.readline()
        self.next_command = Command(text)
    
    
