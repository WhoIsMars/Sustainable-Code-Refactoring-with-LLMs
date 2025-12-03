import json

class RestAPI:
    def __init__(self, database=None):
        self.database = {user['name']: user for user in database['users']}

    def _get_user(self, username):
        return self.database.get(username)

    def lend(self, borrower_name, lender_name, amount):
        borrower = self._get_user(borrower_name)
        lender = self._get_user(lender_name)

        borrower_owes = borrower['owes'].get(lender_name, 0)
        lender_owed_by = lender['owed_by'].get(borrower_name, 0)

        net_amount = amount - lender_owed_by + borrower_owes

        if net_amount > 0:
            borrower['owes'][lender_name] = net_amount
            lender['owed_by'][borrower_name] = net_amount
        else:
            borrower['owes'].pop(lender_name, None)
            lender['owed_by'].pop(borrower_name, None)

        borrower['balance'] -= amount
        lender['balance'] += amount

        return {'users': sorted([borrower, lender], key=lambda v: v['name'])}

    def get(self, url, payload=None):
        if url == '/users':
            if payload:
                data = json.loads(payload)
                users = [self._get_user(name) for name in data['users']]
            else:
                users = list(self.database.values())
            return json.dumps({'users': sorted(users, key=lambda v: v['name'])})

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