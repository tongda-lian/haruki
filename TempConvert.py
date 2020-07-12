# If input temperature is lower than absolute zero (0K)
# Print following message
def wrong_input_under_absolute_zero():
    print("===== The temperature is lower than absolute zero. =====")
    print("===== It has no meaning. =====")

print("***** Temperature Convert *****")
print("***** Programmed by Lian Tongda *****")

while True:

# Print the message, then input a temperature
    TempStr = input("Please input the temperature with symbol F or C.\nExample: 37C or 98F.\nOr input \"exit\" to exit.\n")

# Convert F to C
    if TempStr[-1] in ['F', 'f']:
        if eval(TempStr[0:-1]) >= -459.66 :
            C = (eval(TempStr[0:-1])- 32) / 1.8
#    print("Celsius Temperature is {:.2f}C".format(C))
            print("=====", TempStr, "=", C,"C", "=====")
        else:
            wrong_input_under_absolute_zero()

# Convert C to F
    elif TempStr[-1] in ['C', 'c']:
        if eval(TempStr[0:-1]) >= -273.15 :
            F = 1.8 * eval(TempStr[0:-1]) + 32.0
#	print("Fahrenheit Temperature is {:.2f}F".format(F))
            print("=====", TempStr, "=", F,"F","=====")
        else:
            wrong_input_under_absolute_zero()

# Exit this function
    elif TempStr == "exit":
        break
        
# Wrong format
    else:
        print("\n===== Wrong format! =====\n")

print("===== Exit the program. Goodbye. =====")
