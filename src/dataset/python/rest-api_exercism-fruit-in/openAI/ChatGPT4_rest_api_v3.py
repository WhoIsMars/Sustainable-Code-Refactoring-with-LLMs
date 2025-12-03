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
            lender, borrower, amount = payload["lender"], payload["borrower"], payload["amount"]
            lender_user = next(user for user in self.database["users"] if user["name"] == lender)
            borrower_user = next(user for user in self.database["users"] if user["name"] == borrower)

            lender_user["balance"] += amount
            borrower_user["balance"] -= amount

            if borrower in lender_user["owes"]:
                debt = min(lender_user["owes"][borrower], amount)
                lender_user["owes"][borrower] -= debt
                if lender_user["owes"][borrower] == 0:
                    del lender_user["owes"][borrower]
                amount -= debt

            if amount > 0:
                lender_user["owed_by"][borrower] = lender_user["owed_by"].get(borrower, 0) + amount

            if lender in borrower_user["owed_by"]:
                debt = min(borrower_user["owed_by"][lender], amount)
                borrower_user["owed_by"][lender] -= debt
                if borrower_user["owed_by"][lender] == 0:
                    del borrower_user["owed_by"][lender]
                amount -= debt

            if amount > 0:
                borrower_user["owes"][lender] = borrower_user["owes"].get(lender, 0) + amount

            return json.dumps({"users": sorted([lender_user, borrower_user], key=lambda user: user["name"])})