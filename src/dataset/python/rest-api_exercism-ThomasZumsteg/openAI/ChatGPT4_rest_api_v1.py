import json

class RestAPI(object):
    def __init__(self, database=None):
        self.database = database
        self.users = {user['name']: user for user in database['users']}

    def _get_user(self, username):
        return self.users.get(username)

    def lend(self, borrower_name, lender_name, amount):
        borrower = self._get_user(borrower_name)
        lender = self._get_user(lender_name)

        borrower_owes = borrower['owes'].get(lender_name, 0)
        lender_owed_by = lender['owed_by'].get(borrower_name, 0)

        if lender_owed_by > 0:
            if amount <= lender_owed_by:
                lender['owed_by'][borrower_name] -= amount
                if lender['owed_by'][borrower_name] == 0:
                    del lender['owed_by'][borrower_name]
            else:
                borrower['owes'][lender_name] = amount - lender_owed_by
                del lender['owed_by'][borrower_name]
            borrower['balance'] -= amount
            lender['balance'] += amount
        elif borrower_owes > 0:
            if amount <= borrower_owes:
                borrower['owes'][lender_name] -= amount
                if borrower['owes'][lender_name] == 0:
                    del borrower['owes'][lender_name]
            else:
                lender['owed_by'][borrower_name] = amount - borrower_owes
                del borrower['owes'][lender_name]
            borrower['balance'] -= amount
            lender['balance'] += amount
        else:
            borrower['owes'][lender_name] = borrower['owes'].get(lender_name, 0) + amount
            lender['owed_by'][borrower_name] = lender['owed_by'].get(borrower_name, 0) + amount
            borrower['balance'] -= amount
            lender['balance'] += amount

        return {'users': sorted([borrower, lender], key=lambda v: v['name'])}

    def get(self, url, payload=None):
        if url == '/users':
            if payload:
                data = json.loads(payload)
                users = [self._get_user(name) for name in data['users']]
            else:
                users = list(self.users.values())
            return json.dumps({'users': sorted(users, key=lambda v: v['name'])})

    def post(self, url, payload=None):
        data = json.loads(payload)
        if url == '/add':
            new_user = {
                'name': data['user'],
                'owes': {},
                'owed_by': {},
                'balance': 0
            }
            self.users[data['user']] = new_user
            return json.dumps(new_user)
        elif url == '/iou':
            return json.dumps(self.lend(data['borrower'], data['lender'], data['amount']))