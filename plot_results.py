import pandas as pd
import matplotlib.pyplot as plt
import os

# Read the CSV files
csv_file_vector_sum = 'data_vector_sum.csv'
csv_file_indirect_sum = 'data_indirect_sum.csv'
csv_file_direct_sum = 'data_direct_sum.csv'

df_vector_sum = pd.read_csv(csv_file_vector_sum)
df_indirect_sum = pd.read_csv(csv_file_indirect_sum)
df_direct_sum = pd.read_csv(csv_file_direct_sum)

# Create figures for each metric
fig_bandwidth, ax_bandwidth = plt.subplots(figsize=(10, 6))
fig_mflops, ax_mflops = plt.subplots(figsize=(10, 6))
fig_latency, ax_latency = plt.subplots(figsize=(10, 6))

# Plot Bandwidth Utilization
ax_bandwidth.plot(df_vector_sum['Problem Size'], df_vector_sum['bandwidth util'], marker='o', label='Vector Sum')
ax_bandwidth.plot(df_indirect_sum['Problem Size'], df_indirect_sum['bandwidth util'], marker='s', label='Indirect Sum')
ax_bandwidth.plot(df_direct_sum['Problem Size'], df_direct_sum['bandwidth util'], marker='^', label='Direct Sum')
ax_bandwidth.set_xlabel('Problem Size')
ax_bandwidth.set_ylabel('Bandwidth Utilization (%)')
ax_bandwidth.set_xscale('log', base=2)
ax_bandwidth.set_title('Bandwidth Utilization vs Problem Size')
ax_bandwidth.legend()
ax_bandwidth.grid(True)

# Plot MFLOPS
ax_mflops.plot(df_vector_sum['Problem Size'], df_vector_sum['mflops'], marker='o', label='Vector Sum')
ax_mflops.plot(df_indirect_sum['Problem Size'], df_indirect_sum['mflops'], marker='s', label='Indirect Sum')
ax_mflops.plot(df_direct_sum['Problem Size'], df_direct_sum['mflops'], marker='^', label='Direct Sum')
ax_mflops.set_xlabel('Problem Size')
ax_mflops.set_ylabel('MFLOPS')
ax_mflops.set_xscale('log', base=2)
ax_mflops.set_title('MFLOPS vs Problem Size')
ax_mflops.legend()
ax_mflops.grid(True)

# Plot Memory Latency
ax_latency.plot(df_vector_sum['Problem Size'], df_vector_sum['memory latency'], marker='o', label='Vector Sum')
ax_latency.plot(df_indirect_sum['Problem Size'], df_indirect_sum['memory latency'], marker='s', label='Indirect Sum')
ax_latency.plot(df_direct_sum['Problem Size'], df_direct_sum['memory latency'], marker='^', label='Direct Sum')
ax_latency.set_xlabel('Problem Size')
ax_latency.set_ylabel('Memory Latency (ns)')
ax_latency.set_xscale('log', base=2)
ax_latency.set_title('Memory Latency vs Problem Size')
ax_latency.legend()
ax_latency.grid(True)

# Adjust layout and save plots
plt.tight_layout()

# Save the plots as images
fig_bandwidth.savefig('bandwidth_utilization.png')
fig_mflops.savefig('mflops.png')
fig_latency.savefig('memory_latency.png')

# Close the plots to free up memory
plt.close(fig_bandwidth)
plt.close(fig_mflops)
plt.close(fig_latency)