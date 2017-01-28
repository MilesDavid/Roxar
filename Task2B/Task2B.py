import os
import argparse

import lasparser

# Task 2B:
# Get information from bunch of LAS files.
# LAS is STANDARD FOR LOG DATA,
# Canadian Well Logging Society
# FORMAT VERSION 1.2/2.0

# Write a command line utility inputs user defined path, find all files with LAS
# extension (recursive scan all subfolders, extension case insensitive) and
# produce this output (depends on provided options):

# List all distinct wells in these files (/W option)
# List all distinct oil fields in these files (/F option)
# List all distinct curve mnemo in these files (/C option)
# List all distinct units in these files (/C option)
# May be /U option in list units ?

if __name__ == '__main__':
    try:
        argParser = argparse.ArgumentParser(description='Program for parsing *.las file.')
        
        #  args
        argParser.add_argument('PATH', type=str, action='store', nargs=1, help='Path to *.las files.')
        argParser.add_argument('-W', '--WELLS',action='store_true', help='List all distinct wells in these files')
        argParser.add_argument('-F', '--OIL_FIELDS', action='store_true', help='List all distinct oil fields in these files')
        argParser.add_argument('-C', '--CURVE_MNEMOS', action='store_true', help='List all distinct curve mnemo in these files')
        argParser.add_argument('-U', '--UNITS', action='store_true', help='List all distinct units in these files')
    
        args = argParser.parse_args()
        path = args.PATH[0]

        if os.path.isdir(path):
            parser = lasparser.LasParser()
            parser.parseFiles(path)

            if parser.getFiles():
                if args.WELLS:
                    wells = parser.getDistWells()
                    if wells:
                        print('Dictinct wells:\n{}\n'.format(wells))
                    else:
                        print('Wells not found in *.las files from "{}"'.format(path))

                if args.OIL_FIELDS:
                    oliFields = parser.getDistOilFields()
                    if oliFields:
                        print('Dictinct oli fields:\n{}\n'.format(oliFields))
                    else:
                        print('*.las files not found in "{}"'.format(path))

                if args.CURVE_MNEMOS:
                    curveMnemos = parser.getDistCurveMnemo()
                    if curveMnemos:
                        print('Dictinct curve mnemos:\n{}\n'.format(curveMnemos))
                    else:
                        print('*.las files not found in "{}"'.format(path))

                if args.UNITS:
                    units = parser.getDistUnits()
                    if units:
                        print('Dictinct units:\n{}\n'.format(units))
                    else:
                        print('*.las files not found in "{}"'.format(path))
            else:
                print('\n*.las files not found in "{}"'.format(path))
        else:
            print('\nDirectory "{}" is not exits!'.format(args.path[0]))
    
    # Workaround for argParse
    except SystemExit as e:
        print()
        argParser.print_help()
