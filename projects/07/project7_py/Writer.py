class Writer():
    
    def init(self,filename):
        self.output = open(self.output_filename(filename), 'w')
        
    def write(self,command):
        self.output.write(command)
        
    def close_file(self):
        self.output.close()
        
    def output_filename(self,filename):
        return filename.split('.')[0] + '.asm'
