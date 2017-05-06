def rat_est(number, precision):
	numerator = 1
	denominator = 1
	for i in range(precision):
		if(numerator/denominator==number):
			return str(numerator)+"/"+str(denominator)
		elif(numerator/denominator>number):
			denominator = denominator+1
		elif(numerator/denominator<number):
			numerator = numerator+1
	return str(numerator)+"/"+str(denominator)
