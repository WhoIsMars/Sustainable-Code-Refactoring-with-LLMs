import json

class RestAPI:
    def __init__(self, database=None):
        self.database = database or {'users': []}
        self.user_map = {user['name']: user for user in self.database['users']}

    def _select_username(self, username):
        return self.user_map.get(username)

    def lend(self, borrower_name, lender_name, amount):
        borrower = self._select_username(borrower_name)
        lender = self._select_username(lender_name)

        borrower_owed = borrower['owed_by'].get(lender_name, 0)
        lender_owes = lender['owes'].get(borrower_name, 0)

        if borrower_owed:
            if amount <= borrower_owed:
                borrower['owed_by'][lender_name] -= amount
                if borrower['owed_by'][lender_name] == 0:
                    del borrower['owed_by'][lender_name]
            else:
                borrower['owes'][lender_name] = amount - borrower_owed
                del borrower['owed_by'][lender_name]
        else:
            borrower['owes'][lender_name] = borrower['owes'].get(lender_name, 0) + amount

        if lender_owes:
            if amount <= lender_owes:
                lender['owes'][borrower_name] -= amount
                if lender['owes'][borrower_name] == 0:
                    del lender['owes'][borrower_name]
            else:
                lender['owed_by'][borrower_name] = amount - lender_owes
                del lender['owes'][borrower_name]
        else:
            lender['owed_by'][borrower_name] = lender['owed_by'].get(borrower_name, 0) + amount

        borrower['balance'] -= amount
        lender['balance'] += amount

        return {'users': sorted([lender, borrower], key=lambda v: v['name'])}

    def get(self, url, payload=None):
        if url == '/users':
            if payload:
                data = json.loads(payload)
                users = [self._select_username(name) for name in data['users']]
                result = {'users': users}
            else:
                result = {'users': self.database['users']}
            return json.dumps(result)

    def post(self, url, payload=None):
        data = json.loads(payload)
        if url == '/add':
            new_user = {
                'name': data['user'],
                'owes': {},
                'owed_by': {},
                'balance': 0
            }
            self.database['users'].append(new_user)
            self.user_map[data['user']] = new_user
            return json.dumps(new_user)
        elif url == '/iou':
            return json.dumps(self.lend(data['borrower'], data['lender'], data['amount']))