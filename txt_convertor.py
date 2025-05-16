import math

def polar_to_cartesian(r, theta_deg, z_mm, offset_cm):
    theta_rad = math.radians(theta_deg)
    r_total = offset_cm - r
    x = round((r_total * math.cos(theta_rad) * 100), 2)
    y = round((r_total * math.sin(theta_rad) * 100), 2)
    return f"{x:.2f},{y:.2f},{z_mm * 15:.2f}"

filename = r"path\to\your\file"   
output_filename = r"path\to\your\output_file"
# Replace with the actual path to your file

with open(filename) as file:
    lines = [l.strip() for l in file]

with open(output_filename, 'w') as out_file:
    for i in range(len(lines) // 201):
        for j in range(200):
            out_file.write(polar_to_cartesian(float(lines[i * 201 + j]), 1.8 * j, i, 9.2) + '\n')
        out_file.write('\n')

    l = [[] for _ in range(200)]
    for j in range(200):
        for t in range(j, len(lines), 201):
            l[j].append(polar_to_cartesian(float(lines[t]), 1.8 * j, t // 201, 9.2))

    for sublist in l:
        for element in sublist:
            out_file.write(element + "\n")
        out_file.write("\n")
