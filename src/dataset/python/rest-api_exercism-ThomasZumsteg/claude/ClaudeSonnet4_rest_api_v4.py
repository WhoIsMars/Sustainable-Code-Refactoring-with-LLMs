import json

class RestAPI(object):
    def __init__(self, database=None):
        self.database = database
        self._user_cache = {}
        if database and 'users' in database:
            for user in database['users']:
                self._user_cache[user['name']] = user

    def _select_username(self, username):
        if username in self._user_cache:
            return self._user_cache[username]
        
        for user in self.database['users']:
            if user['name'] == username:
                self._user_cache[username] = user
                return user
        return None
    
    def lend(self, borrower_name, lender_name, amount):
        borrower = self._select_username(borrower_name)
        lender = self._select_username(lender_name)

        borrower_owed_by = borrower['owed_by']
        borrower_owes = borrower['owes']
        lender_owes = lender['owes']
        lender_owed_by = lender['owed_by']

        if lender_name in borrower_owed_by:
            existing_debt = borrower_owed_by[lender_name]
            if amount < existing_debt:
                borrower_owed_by[lender_name] = existing_debt - amount
            else:
                del borrower_owed_by[lender_name]
                if amount != existing_debt:
                    borrower_owes[lender_name] = amount - existing_debt
        else:
            borrower_owes[lender_name] = borrower_owes.get(lender_name, 0) + amount
        
        borrower['balance'] -= amount

        if borrower_name in lender_owes:
            existing_debt = lender_owes[borrower_name]
            if amount < existing_debt:
                lender_owes[borrower_name] = existing_debt - amount
            else:
                del lender_owes[borrower_name]
                if amount != existing_debt:
                    lender_owed_by[borrower_name] = amount - existing_debt
        else:
            lender_owed_by[borrower_name] = lender_owed_by.get(borrower_name, 0) + amount
        
        lender['balance'] += amount

        return {'users': [lender, borrower] if lender['name'] < borrower['name'] else [borrower, lender]}

    def get(self, url, payload=None):
        if url == '/users':
            if payload is None:
                result = self.database
            else:
                data = json.loads(payload)
                result = {'users': [self._select_username(data['users'])]}
        return json.dumps(result, separators=(',', ':'))

    def post(self, url, payload=None):
        data = json.loads(payload)
        
        if url == '/add':
            user_data = {
                'name': data['user'],
                'owes': {},
                'owed_by': {},
                'balance': 0
            }
            self.database['users'].append(user_data)
            self._user_cache[data['user']] = user_data
            result = user_data
        elif url == '/iou':
            result = self.lend(data['borrower'], data['lender'], data['amount'])
        
        return json.dumps(result, separators=(',', ':'))