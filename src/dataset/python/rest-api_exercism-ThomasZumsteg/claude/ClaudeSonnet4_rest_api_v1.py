import json
from collections import defaultdict

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

        # Update borrower
        if lender_name in borrower['owed_by']:
            owed_amount = borrower['owed_by'][lender_name]
            if amount < owed_amount:
                borrower['owed_by'][lender_name] = owed_amount - amount
            else:
                del borrower['owed_by'][lender_name]
                if amount > owed_amount:
                    borrower['owes'][lender_name] = amount - owed_amount
        else:
            borrower['owes'][lender_name] = borrower['owes'].get(lender_name, 0) + amount
        borrower['balance'] -= amount

        # Update lender
        if borrower_name in lender['owes']:
            owes_amount = lender['owes'][borrower_name]
            if amount < owes_amount:
                lender['owes'][borrower_name] = owes_amount - amount
            else:
                del lender['owes'][borrower_name]
                if amount > owes_amount:
                    lender['owed_by'][borrower_name] = amount - owes_amount
        else:
            lender['owed_by'][borrower_name] = lender['owed_by'].get(borrower_name, 0) + amount
        lender['balance'] += amount

        return {'users': sorted([lender, borrower], key=lambda v: v['name'])}

    def get(self, url, payload=None):
        if url == '/users':
            if payload is None:
                result = self.database
            else:
                data = json.loads(payload)
                result = {'users': [self._select_username(data['users'])]}
        return json.dumps(result)

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
        
        return json.dumps(result)