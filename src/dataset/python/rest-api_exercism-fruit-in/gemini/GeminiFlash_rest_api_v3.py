import json


class RestAPI:
    def __init__(self, database=None):
        self.database = database
        self.user_index = {user["name"]: user for user in self.database["users"]} if database else {}

    def get(self, url, payload=None):
        if url == "/users":
            if payload:
                try:
                    payload = json.loads(payload)
                    user_names = payload.get("users", [])
                except (TypeError, json.JSONDecodeError):
                    return json.dumps({"users": []})
            else:
                return json.dumps({"users": []})

            users = [self.user_index[name] for name in user_names if name in self.user_index]
            return json.dumps({"users": sorted(users, key=lambda user: user["name"])})
        return None

    def post(self, url, payload=None):
        if payload:
            try:
                payload = json.loads(payload)
            except (TypeError, json.JSONDecodeError):
                return None
        else:
            return None

        if url == "/add":
            user_name = payload.get("user")
            if not user_name:
                return None

            user = {"name": user_name, "owes": {}, "owed_by": {}, "balance": 0.0}
            self.database["users"].append(user)
            self.user_index[user_name] = user
            return json.dumps(user)
        elif url == "/iou":
            lender_name = payload.get("lender")
            borrower_name = payload.get("borrower")
            amount = payload.get("amount")

            if not all([lender_name, borrower_name, amount]):
                return None

            lender = self.user_index.get(lender_name)
            borrower = self.user_index.get(borrower_name)

            if not lender or not borrower:
                return json.dumps({"users": []})

            lender["balance"] += amount
            borrower["balance"] -= amount

            def update_debt(creditor, debtor, amount):
                if debtor in creditor["owes"]:
                    if creditor["owes"][debtor] > amount:
                        creditor["owes"][debtor] -= amount
                        amount = 0
                    else:
                        amount -= creditor["owes"][debtor]
                        creditor["owes"].pop(debtor)

                if amount > 0:
                    if debtor not in creditor["owed_by"]:
                        creditor["owed_by"][debtor] = 0
                    creditor["owed_by"][debtor] += amount

            update_debt(lender, borrower, amount)
            update_debt(borrower, lender, amount)

            return json.dumps({"users": [lender, borrower]})
        return None