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

        borrower_owed_by = borrower['owed_by']
        borrower_owes = borrower['owes']

        if lender_name in borrower_owed_by:
            owed_amount = borrower_owed_by[lender_name]
            if amount < owed_amount:
                borrower_owed_by[lender_name] -= amount
            else:
                difference = amount - owed_amount
                if difference != 0:
                    borrower_owes[lender_name] = difference
                del borrower_owed_by[lender_name]
        else:
            borrower_owes[lender_name] = borrower_owes.get(lender_name, 0) + amount
        borrower['balance'] -= amount

        lender_owes = lender['owes']
        lender_owed_by = lender['owed_by']

        if borrower_name in lender_owes:
            owes_amount = lender_owes[borrower_name]
            if amount < owes_amount:
                lender_owes[borrower_name] -= amount
            else:
                difference = amount - owes_amount
                if difference != 0:
                    lender_owed_by[borrower_name] = difference
                del lender_owes[borrower_name]
        else:
            lender_owed_by[borrower_name] = lender_owed_by.get(borrower_name, 0) + amount
        lender['balance'] += amount

        return {'users': sorted([lender, borrower], key=lambda v: v['name'])}

    def get(self, url, payload=None):
        if payload:
            try:
                data = json.loads(payload)
            except json.JSONDecodeError:
                return json.dumps({"error": "Invalid JSON payload"})
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
            return json.dumps({"error": "Invalid URL"})

    def post(self, url, payload=None):
        try:
            data = json.loads(payload)
        except (TypeError, json.JSONDecodeError):
            return json.dumps({"error": "Invalid JSON payload"})

        result = {}
        if url == '/add':
            user_name = data.get('user')
            if user_name:
                new_user = {
                    'name': user_name,
                    'owes': {},
                    'owed_by': {},
                    'balance': 0
                }
                self.database['users'].append(new_user)
                self.user_index[user_name] = new_user
                result = new_user
            else:
                result = {"error": "Missing 'user' field in payload"}
        elif url == '/iou':
            borrower = data.get('borrower')
            lender = data.get('lender')
            amount = data.get('amount')
            if borrower and lender and amount is not None:
                result = self.lend(borrower, lender, amount)
            else:
                result = {"error": "Missing 'borrower', 'lender', or 'amount' field in payload"}
        else:
            result = {"error": "Invalid URL"}
        return json.dumps(result)