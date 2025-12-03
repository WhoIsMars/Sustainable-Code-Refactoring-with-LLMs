import json

class RestAPI(object):
    def __init__(self, database=None):
        self.database = {user['name']: user for user in database['users']} if database else {}

    def lend(self, borrower_name, lender_name, amount):
        borrower = self.database.get(borrower_name)
        lender = self.database.get(lender_name)

        if not borrower or not lender:
            return json.dumps({'error': 'Borrower or lender not found'})

        borrower_owed_by = borrower['owed_by']
        borrower_owes = borrower['owes']
        lender_owes = lender['owes']
        lender_owed_by = lender['owed_by']

        if lender_name in borrower_owed_by:
            owed = borrower_owed_by[lender_name]
            if amount < owed:
                borrower_owed_by[lender_name] -= amount
            elif amount > owed:
                borrower_owes[lender_name] = borrower_owes.get(lender_name, 0) + (amount - owed)
                del borrower_owed_by[lender_name]
            else:
                del borrower_owed_by[lender_name]
        else:
            borrower_owes[lender_name] = borrower_owes.get(lender_name, 0) + amount
        borrower['balance'] -= amount

        if borrower_name in lender_owes:
            owes = lender_owes[borrower_name]
            if amount < owes:
                lender_owes[borrower_name] -= amount
            elif amount > owes:
                lender_owed_by[borrower_name] = lender_owed_by.get(borrower_name, 0) + (amount - owes)
                del lender_owes[borrower_name]
            else:
                del lender_owes[borrower_name]
        else:
            lender_owed_by[borrower_name] = lender_owed_by.get(borrower_name, 0) + amount
        lender['balance'] += amount

        return json.dumps({'users': sorted([lender, borrower], key=lambda v: v['name'])})

    def get(self, url, payload=None):
        if url == '/users':
            if payload is None:
                result = {'users': list(self.database.values())}
            else:
                data = json.loads(payload)
                user = self.database.get(data['users'])
                result = {'users': [user]} if user else {'users': []}
            return json.dumps(result)
        return json.dumps({})

    def post(self, url, payload=None):
        data = json.loads(payload)
        if url == '/add':
            user = data['user']
            if user not in self.database:
                self.database[user] = {
                    'name': user,
                    'owes': {},
                    'owed_by': {},
                    'balance': 0
                }
                return json.dumps(self.database[user])
            else:
                return json.dumps({'error': 'User already exists'})
        elif url == '/iou':
            return self.lend(data['borrower'], data['lender'], data['amount'])
        return json.dumps({})