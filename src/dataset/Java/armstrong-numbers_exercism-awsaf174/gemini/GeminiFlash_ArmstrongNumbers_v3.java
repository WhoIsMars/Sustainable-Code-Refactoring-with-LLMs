class ArmstrongNumbers {

	boolean isArmstrongNumber(int numberToCheck) {
		int number = numberToCheck;
		int sum = 0;
		int digits = 0;
		int temp = numberToCheck;

		while (temp != 0) {
			temp /= 10;
			digits++;
		}

		temp = number;
		while (temp != 0) {
			int digit = temp % 10;
			sum += Math.pow(digit, digits);
			temp /= 10;
		}

		return sum == number;
	}
}