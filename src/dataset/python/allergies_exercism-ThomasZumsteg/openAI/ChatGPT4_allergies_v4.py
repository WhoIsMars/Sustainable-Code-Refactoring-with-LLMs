class Allergies:
    allergie_list = ['eggs', 'peanuts', 'shellfish', 'strawberries', 
                     'tomatoes', 'chocolate', 'pollen', 'cats']

    def __init__(self, score):
        self.lst = [allergie for i, allergie in enumerate(self.allergie_list) if score & (1 << i)]

    def is_allergic_to(self, allergie):
        return allergie in self.lst