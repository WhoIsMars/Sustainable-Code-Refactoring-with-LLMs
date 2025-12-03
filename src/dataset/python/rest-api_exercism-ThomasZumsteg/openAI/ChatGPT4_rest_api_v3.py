import json

class RestAPI(object):
    def __init__(self, database=None):
        self.database = {user['name']: user for user in database['users']}

    def _select_username(self, username):
        return self.database.get(username)

    def lend(self, borrower_name, lender_name, amount):
        borrower = self._select_username(borrower_name)
        lender = self._select_username(lender_name)

        borrower_owes = borrower['owes']
        borrower_owed_by = borrower['owed_by']
        lender_owes = lender['owes']
        lender_owed_by = lender['owed_by']

        if lender_name in borrower_owed_by:
            if amount < borrower_owed_by[lender_name]:
                borrower_owed_by[lender_name] -= amount
            else:
                if amount > borrower_owed_by[lender_name]:
                    borrower_owes[lender_name] = amount - borrower_owed_by[lender_name]
                del borrower_owed_by[lender_name]
        else:
            borrower_owes[lender_name] = borrower_owes.get(lender_name, 0) + amount
        borrower['balance'] -= amount

        if borrower_name in lender_owes:
            if amount < lender_owes[borrower_name]:
                lender_owes[borrower_name] -= amount
            else:
                if amount > lender_owes[borrower_name]:
                    lender_owed_by[borrower_name] = amount - lender_owes[borrower_name]
                del lender_owes[borrower_name]
        else:
            lender_owed_by[borrower_name] = lender_owed_by.get(borrower_name, 0) + amount
        lender['balance'] += amount

        return {'users': sorted([lender, borrower], key=lambda v: v['name'])}

    def get(self, url, payload=None):
        if url == '/users':
            if payload:
                data = json.loads(payload)
                users = [self._select_username(user) for user in data['users']]
                result = {'users': users}
            else:
                result = {'users': list(self.database.values())}
            return json.dumps(result)

    def post(self, url, payload=None):
        data = json.loads(payload)
        if url == '/add':
            user = {
                'name': data['user'],
                'owes': {},
                'owed_by': {},
                'balance': 0
            }
            self.database[data['user']] = user
            return json.dumps(user)
        elif url == '/iou':
            return json.dumps(self.lend(data['borrower'], data['lender'], data['amount']))