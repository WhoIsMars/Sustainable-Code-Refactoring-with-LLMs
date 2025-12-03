export default class Bob {
  hey(message: string): string {
    const trimmedMessage = message.trim();
    if (!trimmedMessage) return 'Fine. Be that way!';
    const isYelling = /[A-Z]/.test(trimmedMessage) && trimmedMessage === trimmedMessage.toUpperCase();
    const isQuestion = trimmedMessage.endsWith('?');
    if (isYelling) return 'Whoa, chill out!';
    if (isQuestion) return 'Sure.';
    return 'Whatever.';
  }
}