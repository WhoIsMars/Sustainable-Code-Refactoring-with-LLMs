import json


class RestAPI:
    def __init__(self, database=None):
        self.database = database

    def get(self, url, payload=None):
        if payload is not None:
            payload = json.loads(payload)
            if url == "/users":
                user_names = set(payload["users"])
                users = [user for user in self.database["users"]
                         if user["name"] in user_names]
                users.sort(key=lambda user: user["name"])
                return json.dumps({"users": users})
        elif url == "/users":
            return json.dumps({"users": []})

    def post(self, url, payload=None):
        if payload is not None:
            payload = json.loads(payload)
        
        if url == "/add":
            if payload is None:
                return json.dumps({})
            user = {"name": payload["user"],
                    "owes": {}, "owed_by": {}, "balance": 0.0}
            self.database["users"].append(user)
            return json.dumps(user)
        elif url == "/iou":
            if payload is None:
                return json.dumps({"users": []})
            
            lender = payload["lender"]
            borrower = payload["borrower"]
            amount = payload["amount"]
            
            lender_user = None
            borrower_user = None
            
            # Find users in single pass
            for user in self.database["users"]:
                if user["name"] == lender:
                    lender_user = user
                elif user["name"] == borrower:
                    borrower_user = user
                if lender_user and borrower_user:
                    break
            
            users = {"users": []}
            
            if lender_user:
                lender_user["balance"] += amount
                remain = amount
                users["users"].append(lender_user)

                if borrower in lender_user["owes"]:
                    owed_amount = lender_user["owes"][borrower]
                    if owed_amount > remain:
                        lender_user["owes"][borrower] -= remain
                        remain = 0
                    else:
                        remain -= owed_amount
                        del lender_user["owes"][borrower]

                if remain > 0:
                    lender_user["owed_by"][borrower] = lender_user["owed_by"].get(borrower, 0) + remain

            if borrower_user:
                borrower_user["balance"] -= amount
                remain = amount
                users["users"].append(borrower_user)

                if lender in borrower_user["owed_by"]:
                    owed_amount = borrower_user["owed_by"][lender]
                    if owed_amount > remain:
                        borrower_user["owed_by"][lender] -= remain
                        remain = 0
                    else:
                        remain -= owed_amount
                        del borrower_user["owed_by"][lender]

                if remain > 0:
                    borrower_user["owes"][lender] = borrower_user["owes"].get(lender, 0) + remain

            return json.dumps(users)