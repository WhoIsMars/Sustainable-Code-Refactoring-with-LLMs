export default class Bob {
  hey(message: string): string {
    const trimmedMessage = message.trim();

    if (!trimmedMessage) {
      return 'Fine. Be that way!';
    }

    const isUpperCase = trimmedMessage === trimmedMessage.toUpperCase();
    const hasLetters = /[A-Za-z]/.test(trimmedMessage);

    if (hasLetters && isUpperCase) {
      return 'Whoa, chill out!';
    }

    if (trimmedMessage.endsWith('?')) {
      return 'Sure.';
    }

    return 'Whatever.';
  }
}