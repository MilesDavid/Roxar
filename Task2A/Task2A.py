from welltraject import welltraject as wt
import sys

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
            # Column 3 ??DY

if __name__ == '__main__':

    path = 'C:\\Users\\borisov.LANAGENT\\Downloads\\???°???????µ\\Trajectory\\10958.txt'

    data = wt.parseFile(path)
    traject = wt.calcWellTrajectory(data)
    wt.writeToFile('.', data)