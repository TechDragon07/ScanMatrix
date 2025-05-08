import math

def polar_to_cartesian(r, theta_deg, z_mm, offset_cm):
    theta_rad = math.radians(theta_deg)
    r_total = offset_cm - r
    x = r_total * math.cos(theta_rad)
    y = r_total * math.sin(theta_rad)
    return f"{x:.4f},{y:.4f},{z_mm}"



filename = 'C:/scans/earphones.TXT'
arrays = []
with open(filename) as file:
    temp_list = []
    lines = [l.strip() for l in file]

l = [[] for _ in range(200)]

for j in range(0,200):
    for t in range(j,len(lines),201):
        l[j].append(polar_to_cartesian(float(lines[t]),1.8*j,t//201,9.2))
output_filename = 'C:/scans/earphones_processed.txt'
with open(output_filename, 'w') as out_file:
    for sublist in l:
        for element in sublist:
            out_file.write(element + "\n")
        out_file.write("\n")