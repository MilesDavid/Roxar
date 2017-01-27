'''This is module contains LasParser class for parsing *.las files'''

import os
import fnmatch
import re

'''Class for parsing *.las files'''
class LasParser(object):
    # section structure:
    # {
    #    Filename1 : {
    #                    section1 : [data1, data2, ...],
    #                    section2 : [data1, data2, ...]
    #                    ...
    #                },
    #    Filename2: ...
    # }

    __sections = dict()

    # List parsed files
    def getFiles(self):
        return self.__sections.keys()

    # Returs raw data from sections
    def getSections(self):
        return self.__sections.values()

    # Recursevely search for *.las files
    def findFiles(self, path):
        matches = []
        for root, dirnames, filenames in os.walk(path):
            for filename in fnmatch.filter(filenames, '*.las'):
                matches.append(os.path.join(root, filename))
        
        return matches

    # Parsing all founded files
    def parseFiles(self, path):
        for file in self.findFiles(path):
            self.parseFile(file)

    # Parse file on sections
    def parseFile(self, path):
        tmp = dict()
        with open(path) as f:
            for line in f:
                if re.match(r'^#.*$', line) or re.match(r'^$', line):
                    continue
                elif re.match(r'^~V.*$', line):
                    sect = 'VERSION'
                    continue
                elif re.match(r'^~W.*$', line):
                    sect = 'WELL'
                    tmp[sect] = []
                    continue
                elif re.match(r'^~P.*$', line):
                    sect = 'PARAMETER'
                    tmp[sect] = []
                    continue
                elif re.match(r'^~C.*$', line):
                    sect = 'CURVE'
                    tmp[sect] = []
                    continue
                elif re.match(r'^~A.*$', line):
                    break
                elif re.match(r'^~.*$', line):
                    sect = 'UNKNOWN_OPTION'
                    continue
                
                if sect == 'WELL' or sect == 'PARAMETER' or sect == 'CURVE':
                    tmp[sect].append(line)

            self.__sections[path] = tmp
    
    # Parse sections on fields
    def parseSection(self, name, sect):
        res = []
        isCurve = True if name == 'CURVE' else False
        for s in sect:
            res.append(self.parseField(s, isCurve))

        return res

    # Parse fields section according to the versions 1.2 and 2
    def parseField(self, s, isCurveSect):
        res = dict()

        tmp = s.split(':', 1)

        if len(tmp) == 2:
            if isCurveSect:
                curveDesc = re.split(r'\s', tmp[1].lstrip(), 1)
                curve = curveDesc[0]
                desc = curveDesc[1] if len(curveDesc) == 2 else ''
            else:
                desc = tmp[1]

            tmp = tmp[0].split('.', 1)
            keyword = tmp[0].strip()

            if re.match(r'^\s', tmp[1][:1]):
                unit = ""
            else:
                tmp = re.split(r'\s', tmp[1], 1)
                unit = tmp[0]
            
            data = tmp[1].strip()

            res['keyword'] = keyword
            res['unit'] = unit
            res['data'] = data

            if isCurveSect:
                res['curve'] = curve

            res['desc'] = desc
            
            return res

    # Returns list all distinct wells in these files
    def getDistWells(self):
        res = set()

        for sectStruct in self.__sections.values():
            for field in self.parseSection('WELL', sectStruct['WELL']):
                if field['keyword'] == 'WELL':
                    res.add(field['data'])

        return res

    # Returns list all distinct oil fields in these files
    def getDistOilFields(self):
        res = set()

        for sectStruct in self.__sections.values():
            for field in self.parseSection('WELL', sectStruct['WELL']):
                if field['keyword'] == 'FLD':
                    res.add(field['data'])

        return res

    # Returns list all distinct curve mnemo in these files
    def getDistCurveMnemo(self):
        res = set()

        for sectStruct in self.__sections.values():
            for field in self.parseSection('CURVE', sectStruct['CURVE']):
                res.add(field['keyword'])

        return res

    # Returns list all distinct units in these files
    def getDistUnits(self):
        res = set()

        for sectStruct in self.__sections.values():
            for sect in sectStruct:
                for field in self.parseSection(sect, sectStruct[sect]):
                    res.add(field['unit'])

        return res