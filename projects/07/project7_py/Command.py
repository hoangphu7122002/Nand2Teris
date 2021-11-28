class Command():
    #symbol
    COMMENT = '//'
    NEWLINE = '\n'
    EMPTY = ''
    
    def __init__(self,text):
        self.raw = text
        self.text = text.strip()
        self.parts = text.strip().split(" ")
        
    def isComment(self):
        return self.raw[0 : 2] == self.COMMENT
    
    def isEMPTY(self):
        return self.raw == self.EMPTY
    
    def isWhiteSpace(self):
        return self.raw == self.NEWLINE
    
    def isPushPop(self):
        return self.parts[0] == 'push' or self.parts[0] == 'pop'
    
    def segment(self):
        if len(self.parts) != 3:
            return
        return self.parts[1]
    
    def index_segment(self):
        if len(self.parts) != 3:
            return 
        return self.parts[2]
    
    def operation(self):
        return self.parts[0]
