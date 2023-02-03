import random, sys
import argparse

class randline:
    def __init__(self, lines, repeat):
        self.lines = lines
        self.repeat = repeat

    def chooseline(self):
        if len(self.lines) == 0:
            raise("Not Enough lines to choose!")
        result = random.choice(self.lines)
        if not self.repeat:
            self.lines.remove(result)
        return result
    
def main():
    parser = argparse.ArgumentParser(prog="shuf",
                                     description='Chenda\'s inplementation on shuf',
                                     allow_abbrev=False)
    parser.add_argument('-r', '--repeat', 
                         dest = "ifrepeat",
                         action='store_true', 
                         default = False,
                         help = "Repeat output values")
    parser.add_argument('-i', '--input-range',
                         metavar='lo-hi',
                         dest = "intputrange",
                         action = "store",
                         nargs=1,
                         type = str,
                         default = None,
                         help = "input came from a file containing the range of unsigned decimal integers lo-hi, one per line."
                         )
    parser.add_argument('-e','--echo',
                         dest = 'echo',
                         action='store_true',
                         default = False,
                         help = "Treat each command-line operand as an input line."
                
                         )
    parser.add_argument('-n', '--head-count', 
                         metavar='count',
                         dest = "numCount",
                         action='store', 
                         nargs=1,
                         type = int, 
                         default= None,
                         help = "Output at most count lines"
                         )
    args, unknown = parser.parse_known_args()
    inputs = unknown
    inputlength = len(inputs)
    realNumCount = 0
    hasCount = True
    isInputRange = False


    if args.echo:
        if(len(inputs) == 0) or args.intputrange != None:
            print("You choose the echo but you did not type anything, or you type -i and -e at the same time")
            return 1
        
        
    else:
        if args.intputrange != None:
            if (len(inputs) == 1 and inputs[0] == '-'):
                print("You should not use inputRange and stdin at the same time")
                return 1
            inputrange = args.intputrange[0]
            try:
                isInputRange = True
                hasCount = True
                start, end = inputrange.split('-')
                startNum = int(start)
                endNum = int(end)
                inputs = []
                if endNum < startNum:
                    print("Your range end should be greater than range start")
                    return 1
                for i in range(startNum,endNum+1):
                    inputs.append(i)
                inputlength = len(inputs)
            except:
                print("inputrangeFormatError")

        elif len(inputs) == 0 or (len(inputs) == 1 and inputs[0] == '-'):
            inputs = sys.stdin.read().splitlines()
            inputlength = len(inputs)
        elif len(inputs) == 1:
            try:
                f = open(inputs[0], 'r')
                inputs = f.read().splitlines()
                inputlength = len(inputs)
            except:
                print("Cannot find the input file")
                return 1
        else:
            print("unknown command!")
            return 1


    if isInputRange:
        if args.numCount == None:
            realNumCount = len(inputs)
            hasCount = False
        else:
            if args.numCount[0] < 0:
                print("-n cannot be negative")
            if not args.ifrepeat and args.numCount[0] > len(inputs):
                realNumCount = len(inputs)
            else:
                realNumCount = args.numCount[0]
    else:
        if args.numCount == None:
            hasCount = False
            realNumCount = inputlength
        else:
            if args.numCount[0] < 0:
                print("-n cannot be negative")
            if not args.ifrepeat and args.numCount[0] > inputlength:
                realNumCount = inputlength
            else:
                realNumCount = args.numCount[0]

    generator = randline(inputs, args.ifrepeat)
    while realNumCount > 0:
        print(generator.chooseline())
        if args.ifrepeat and not hasCount:
            continue
        realNumCount = realNumCount - 1


if __name__ == "__main__":
    main()
