from re import match
from sys import exit

#find which octect to perform the subnet calculation on
def findoctect(subnetlength):
  octect = int(subnetlength / 8)
  if subnetlength % 8 == 0:
    octect -= 1
  return octect

#clear all octects after the one with the subnet calculations
def clearoctect(octect):
  for i in range(3, octect, -1):
    ipaddress[i] = 0

#calculate the new octect based on the modulus of the subnet
def calculatesubnet(subnetlength):
  octectlength = 0
  if subnetlength % 8 != 0:
    octectlength = 8 - subnetlength % 8
  for i in range (0, octectlength):
    #if binary at that digit is 1, subtract
    if ipaddress[octect] % pow(2, i + 1) != 0:
      ipaddress[octect] -= pow(2, i - 0)

#Enter IP Address
while (True):
  ipaddress = input("Please Enter a valid IPv4 Address: ")
  # input must match IP address format
  if match("[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}", ipaddress):
    break

# Split IP address delimited by period
ipaddress = ipaddress.split(".")
# convert string type to int for calculation
ipaddress = [int(i) for i in ipaddress]
# check for valid range of octets
for i in ipaddress:
  #octect must be between 0 to 255
  if i not in range(0, 265):
    print("The IP address you entered cannot be calculated. Please try again.")
    exit(1)

while (True):
  try:
    # cast string input into integer
    subnetlength = int(input("Please enter the Subnet Length: "))
    # break if between 1 to 32
    if subnetlength in range(1, 33):
      break
    # catch exception if a number was not entered
  except:
    print("Please enter a valid subnet length between 0 to 32")

octect = findoctect(subnetlength)
clearoctect(octect)
calculatesubnet(subnetlength)

#permutate the network address
networkaddress = "."
networkaddress = networkaddress.join([str(i) for i in ipaddress])

print(f"The network address of your IP address is: {networkaddress}")

exit(0)