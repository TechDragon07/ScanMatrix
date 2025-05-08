import math

def polar_to_cartesian(r, theta_deg, z_mm, offset_cm):
    theta_rad = math.radians(theta_deg)
    r_total = offset_cm - r
    x = round((r_total * math.cos(theta_rad) * 100), 2)
    y = round((r_total * math.sin(theta_rad) * 100), 2)
    return f"{x:.2f},{y:.2f},{z_mm * 15:.2f}"

filename = 'C:/scans/earphones.TXT'
arrays = []
with open(filename) as file:
    temp_list = []
    lines = [l.strip() for l in file]

output_filename = 'C:/scans/earphones_processed_2.txt'
with open(output_filename, 'w') as out_file:
    for i in range(len(lines) // 201):
        for j in range(200):  # No need for `range(0,200)`, `range(200)` is equivalent
            out_file.write(polar_to_cartesian(float(lines[i * 201 + j]), 1.8 * j, i, 9.2) + '\n')
        out_file.write('\n')

