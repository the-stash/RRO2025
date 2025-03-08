void blackSound() {
	playTone(1500, 17.5);
}

void whiteSound() {
	playTone(850, 12);
}

int toSay[6];

task sayScanned() {
	for (int i = 0; i < 6; i++) {
		if (toSay[i] == 1) {playSoundFile("Black"); sleep(300);}
		else {playSoundFile("White"); sleep(300);}
	}
}

void setArrToSpeak(int *arr) {
	for (int i = 0; i < 6; i++) {
		toSay[i] = arr[i];
	}
}

void peak() {
    playTone(700, 6);
}
