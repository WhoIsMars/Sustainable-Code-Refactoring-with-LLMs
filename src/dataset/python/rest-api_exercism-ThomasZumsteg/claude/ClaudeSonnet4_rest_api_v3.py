import json
from collections import defaultdict

class RestAPI(object):
    def __init__(self, database=None):
        self.database = database or {'users': []}
        self._user_index = {user['name']: user for user in self.database.get('users', [])}

    def _select_username(self, username):
        return self._user_index.get(username)
    
    def _update_debt(self, debtor, creditor, amount, debt_key, credit_key):
        opposite_debt = debtor.get(credit_key, {}).get(creditor, 0)
        
        if opposite_debt > 0:
            if amount <= opposite_debt:
                if amount == opposite_debt:
                    del debtor[credit_key][creditor]
                    if not debtor[credit_key]:
                        debtor[credit_key] = {}
                else:
                    debtor[credit_key][creditor] = opposite_debt - amount
                return 0
            else:
                del debtor[credit_key][creditor]
                if not debtor[credit_key]:
                    debtor[credit_key] = {}
                return amount - opposite_debt
        return amount
    
    def lend(self, borrower_name, lender_name, amount):
        borrower = self._select_username(borrower_name)
        lender = self._select_username(lender_name)

        remaining_amount = self._update_debt(borrower, lender_name, amount, 'owes', 'owed_by')
        if remaining_amount > 0:
            borrower['owes'][lender_name] = borrower['owes'].get(lender_name, 0) + remaining_amount
        borrower['balance'] -= amount

        remaining_amount = self._update_debt(lender, borrower_name, amount, 'owed_by', 'owes')
        if remaining_amount > 0:
            lender['owed_by'][borrower_name] = lender['owed_by'].get(borrower_name, 0) + remaining_amount
        lender['balance'] += amount

        return {'users': [lender, borrower] if lender_name < borrower_name else [borrower, lender]}

    def get(self, url, payload=None):
        if url == '/users':
            if payload is None:
                result = self.database
            else:
                data = json.loads(payload)
                user = self._select_username(data['users'])
                result = {'users': [user]} if user else {'users': []}
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
            self.database.setdefault('users', []).append(user_data)
            self._user_index[data['user']] = user_data
            return json.dumps(user_data)
        elif url == '/iou':
            result = self.lend(data['borrower'], data['lender'], data['amount'])
            return json.dumps(result)