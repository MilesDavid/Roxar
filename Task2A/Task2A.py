from welltraject import welltraject as wt
import sys
import os

# A) Make well trajectory from deviation survey data.
        # Write a command line utility that inputs deviation survey data (text file) with structure:
            # Column 1 -MD (measured depth)
            # Column 2 -Angle 
            # Column 3 Azimuth

        # Columns are separated with: colon, space or tab symbols (all separators are legal simultaneously).
        # Example:
            # 10	0.2	140
            # 20	0.2	141
            # 30	0.2	142
            # 40	0.2	143
            # 50	0.2	144
            # 60	0.3	145
            # 70	0.4	146
            # 80	1	147
            # 90	1.1	148

        # Utility should calculate parameters:
        # - Offset in East direction (DX)
        # - Offset in North direction (DY)
        # - True vertical depth (TVD) from wellhead.

        # Utility should produce trajectory text file:
            # Column 1 -TVD
            # Column 2 -DX
            # Column 3 -DY

def printHelpAndExit(error=''):
    if error: print(error)
    res = 'Description:\n\tCalculates well trajectory by survey deviation data using balanced tangential method\n\n'
    res += 'Usage:\n\t{} input_file output_file\n\n'.format(os.path.basename(sys.argv[0]))
    res += 'positional arguments:\n'
    res += '\tinput_file\t\tPath to survey data file\n'
    res += '\toutput_file\t\tPath to well trajectory file\n'
    print(res)
    input('Press any key to exit\n')
    sys.exit()

if __name__ == '__main__':
    try:
        MAX_ARGS = 3
        if len(sys.argv) != MAX_ARGS:
            printHelpAndExit()

        if not os.path.isfile(sys.argv[1]):
            printHelpAndExit('\nFile "{}" not found in "{}"..\n'.format(
                os.path.basename(sys.argv[1]),
                os.path.dirname(sys.argv[1]))
            )

        if not os.path.isdir(os.path.dirname(sys.argv[2])):
            printHelpAndExit('\nDirectory "{}" not found..\n'.format(os.path.dirname(sys.argv[2])))
            
        inputFile = sys.argv[1]
        outputFile = sys.argv[2]

        data = wt.parseFile(inputFile)
        traject = wt.calcWellTrajectory(data)
        wt.writeToFile(outputFile, traject)
    except SystemExit:
        pass