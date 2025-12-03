export default class Bob {
  hey(message: string): string {
    const trimmedMessage = message.trim();
    if (!trimmedMessage) return 'Fine. Be that way!';
    const isYelling = /^[^a-z]*[A-Z][^a-z]*$/.test(trimmedMessage);
    if (isYelling) return 'Whoa, chill out!';
    if (trimmedMessage.endsWith('?')) return 'Sure.';
    return 'Whatever.';
  }
}