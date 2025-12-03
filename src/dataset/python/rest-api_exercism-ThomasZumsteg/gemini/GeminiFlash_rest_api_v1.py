import json
from collections import defaultdict

class RestAPI(object):
    def __init__(self, database=None):
        self.database = database
        self.user_index = {user['name']: user for user in self.database['users']} if database else {}

    def _get_user(self, username):
        return self.user_index.get(username)

    def lend(self, borrower_name, lender_name, amount):
        borrower = self._get_user(borrower_name)
        lender = self._get_user(lender_name)

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
            else:
                diff = amount - owed
                if diff != 0:
                    borrower_owes[lender_name] = diff
                del borrower_owed_by[lender_name]
        else:
            borrower_owes[lender_name] = borrower_owes.get(lender_name, 0) + amount
        borrower['balance'] -= amount

        if borrower_name in lender_owes:
            owes = lender_owes[borrower_name]
            if amount < owes:
                lender_owes[borrower_name] -= amount
            else:
                diff = amount - owes
                if diff != 0:
                    lender_owed_by[borrower_name] = diff
                del lender_owes[borrower_name]
        else:
            lender_owed_by[borrower_name] = lender_owed_by.get(borrower_name, 0) + amount
        lender['balance'] += amount

        return { 'users': sorted([lender, borrower], key=lambda v: v['name'])}

    def get(self, url, payload=None):
        if payload:
            try:
                data = json.loads(payload)
            except json.JSONDecodeError:
                return json.dumps({'error': 'Invalid JSON payload'})
        else:
            data = None

        if url == '/users':
            if data is None:
                result = self.database
            else:
                username = data.get('users')
                if username:
                    user = self._get_user(username)
                    result = {'users': [user]} if user else {'users': []}
                else:
                    result = {'users': []}
            return json.dumps(result)
        else:
            return json.dumps({'error': 'Invalid URL'})


    def post(self, url, payload=None):
        try:
            data = json.loads(payload)
        except (json.JSONDecodeError, TypeError):
            return json.dumps({'error': 'Invalid JSON payload'})

        if url == '/add':
            user = data.get('user')
            if not user:
                return json.dumps({'error': 'User not specified'})
            
            new_user = {
                'name': user,
                'owes': {},
                'owed_by': {},
                'balance': 0
            }
            
            if self.database is None:
                self.database = {'users': []}

            self.database['users'].append(new_user)
            self.user_index[user] = new_user
            return json.dumps(new_user)

        elif url == '/iou':
            borrower = data.get('borrower')
            lender = data.get('lender')
            amount = data.get('amount')

            if not all([borrower, lender, amount]):
                return json.dumps({'error': 'Missing borrower, lender, or amount'})
            
            return json.dumps(self.lend(borrower, lender, amount))
        else:
            return json.dumps({'error': 'Invalid URL'})