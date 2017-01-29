import os
import re
import sys
import math

class welltraject(object):
    """
        This class calculates well trajectory by survey deviation data.
	    Class uses for calculations balanced tangential method.
    """

    # Returns list of [MD, Angle, Azimuth]
    @staticmethod
    def parseFile(path, columns=3):
        res = []
    
        if os.path.isfile(path):
            with open(path) as f:
                for line in f:
                    if not re.match(r'^#.*$', line):
                        tmp = re.split(r':|\s+', line)
                        tmp = list(filter(lambda x: x != '', tmp))
                        tmp = [float(i) for i in tmp]
                        res.append(tmp[:3])

        return res

    # Returns well trajectory (list of [TVD, North, East])
    # from deviation survey data by balanced tangential method
    @staticmethod
    def calcWellTrajectory(data):
        # Balanced
        # North = SUM (MD2 - MD1) * ((Sin WD1 * Cos HAZ1 + Sin WD2 * Cos HAZ2) / 2)
        # East = SUM (MD2 - MD1) * ((Sin WD1 * Sin HAZ1 + Sin WD2 * Sin HAZ2) / 2)
        # TVD = SUM ((MD2 - MD1) * (Cos WD2 + Cos WD1) / 2)
    
        # initialize data for first step
        MD1 = 0.0; WD1 = 0.0; AZ1 = 0.0
        North1 = 0.0; East1 = 0.0; TVD1 = 0.0

        res = []
        for elem in data:
            MD2 = elem[0]; WD2 = elem[1]; AZ2 = elem[2]

            dMD = MD2 - MD1
            radWD1 = math.radians(WD1); radWD2 = math.radians(WD2)
            radAZ1 = math.radians(AZ1); radWAZ2 = math.radians(AZ2)

            sinWD1 = math.sin(math.radians(WD1)); cosWD1 = math.cos(math.radians(WD1))
            sinWD2 = math.sin(math.radians(WD2)); cosWD2 = math.cos(math.radians(WD2))
            sinAZ1 = math.sin(math.radians(AZ1)); cosAZ1 = math.cos(math.radians(AZ1))
            sinAZ2 = math.sin(math.radians(AZ2)); cosAZ2 = math.cos(math.radians(AZ2))

            North2 = dMD * (sinWD1 * cosAZ1 + sinWD2 * cosAZ2) / 2.0 + North1
            East2 = dMD * (sinWD1 * sinAZ1 + sinWD2 * sinAZ2) / 2.0 + East1
            TVD2 = dMD * (cosWD1 + cosWD2) / 2.0 + TVD1
            
            North2 = round(North2, 2); East2 = round(East2, 2); TVD2 = round(TVD2, 2)
 
            MD1 = MD2; WD1 = WD2; AZ1 = AZ2
            North1 = North2; East1 = East2; TVD1 = TVD2
            res.append([TVD2, North2, East2])
        return res

    # Writes well traject to file with header '# TVD North East'
    @staticmethod
    def writeToFile(path, data, offset=20):
        with open(path, 'w') as f:
            commMask = '#{:>'+ str(offset - 1) +'}'
            mask = '{:>'+ str(offset) +'}'
            header = ['TVD', 'North', 'East']

            f.write(commMask.format(header[0]))
            for elem in [header[1:]] + data:
                for e in elem:
                    f.write(mask.format(e))
                f.write('\n')


