import subprocess

num_runs = 10

seg_fault = 0
no_seg_fault = 0
for i in range(1,num_runs):
  res = subprocess.run(["./ex2/build/main_ex2"],stdout=subprocess.PIPE,stderr=subprocess.PIPE)

  # seg fault code error should be 139 https://stackoverflow.com/questions/14599670/what-error-code-does-a-process-that-segfaults-return 
  if res.returncode == 139:
    seg_fault += 1 
  elif res.returncode ==0:
    no_seg_fault += 1
  else:
      print("unexpected returncode: ",res.returncode)

print("program gave",seg_fault,"segmentation fault out of 10 runs")



