import json


class RestAPI:
    def __init__(self, database=None):
        self.database = database

    def get(self, url, payload=None):
        if url == "/users":
            payload_users = set(json.loads(payload)["users"]) if payload else set()
            users = [user for user in self.database["users"] if not payload_users or user["name"] in payload_users]
            return json.dumps({"users": sorted(users, key=lambda user: user["name"])})

    def post(self, url, payload=None):
        payload = json.loads(payload) if payload else {}

        if url == "/add":
            user = {"name": payload["user"], "owes": {}, "owed_by": {}, "balance": 0.0}
            self.database["users"].append(user)
            return json.dumps(user)

        elif url == "/iou":
            lender_name, borrower_name, amount = payload["lender"], payload["borrower"], payload["amount"]
            lender, borrower = None, None

            for user in self.database["users"]:
                if user["name"] == lender_name:
                    lender = user
                elif user["name"] == borrower_name:
                    borrower = user
                if lender and borrower:
                    break

            lender["balance"] += amount
            borrower["balance"] -= amount

            if borrower_name in lender["owes"]:
                if lender["owes"][borrower_name] > amount:
                    lender["owes"][borrower_name] -= amount
                else:
                    amount -= lender["owes"].pop(borrower_name)
            if amount > 0:
                lender["owed_by"][borrower_name] = lender["owed_by"].get(borrower_name, 0) + amount

            if lender_name in borrower["owed_by"]:
                if borrower["owed_by"][lender_name] > amount:
                    borrower["owed_by"][lender_name] -= amount
                else:
                    amount -= borrower["owed_by"].pop(lender_name)
            if amount > 0:
                borrower["owes"][lender_name] = borrower["owes"].get(lender_name, 0) + amount

            return json.dumps({"users": sorted([lender, borrower], key=lambda user: user["name"])})