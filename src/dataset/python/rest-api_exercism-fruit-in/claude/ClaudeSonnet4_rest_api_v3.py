import json


class RestAPI:
    def __init__(self, database=None):
        self.database = database

    def get(self, url, payload=None):
        if payload is not None:
            payload = json.loads(payload)
        else:
            payload = {"users": []}

        if url == "/users":
            if not payload["users"]:
                return json.dumps({"users": []})
            
            user_names = set(payload["users"])
            users = [user for user in self.database["users"] 
                    if user["name"] in user_names]
            
            users.sort(key=lambda user: user["name"])
            return json.dumps({"users": users})

    def post(self, url, payload=None):
        if payload is not None:
            payload = json.loads(payload)
        else:
            payload = {"users": []}

        if url == "/add":
            user = {
                "name": payload["user"],
                "owes": {},
                "owed_by": {},
                "balance": 0.0
            }
            self.database["users"].append(user)
            return json.dumps(user)
        
        elif url == "/iou":
            lender_name = payload["lender"]
            borrower_name = payload["borrower"]
            amount = payload["amount"]
            
            lender = None
            borrower = None
            
            for user in self.database["users"]:
                if user["name"] == lender_name:
                    lender = user
                elif user["name"] == borrower_name:
                    borrower = user
                if lender and borrower:
                    break
            
            self._process_lender(lender, borrower_name, amount)
            self._process_borrower(borrower, lender_name, amount)
            
            return json.dumps({"users": [lender, borrower]})

    def _process_lender(self, lender, borrower_name, amount):
        lender["balance"] += amount
        remain = amount
        
        if borrower_name in lender["owes"]:
            owed_amount = lender["owes"][borrower_name]
            if owed_amount > remain:
                lender["owes"][borrower_name] -= remain
                remain = 0
            else:
                remain -= owed_amount
                del lender["owes"][borrower_name]
        
        if remain > 0:
            lender["owed_by"][borrower_name] = lender["owed_by"].get(borrower_name, 0) + remain

    def _process_borrower(self, borrower, lender_name, amount):
        borrower["balance"] -= amount
        remain = amount
        
        if lender_name in borrower["owed_by"]:
            owed_amount = borrower["owed_by"][lender_name]
            if owed_amount > remain:
                borrower["owed_by"][lender_name] -= remain
                remain = 0
            else:
                remain -= owed_amount
                del borrower["owed_by"][lender_name]
        
        if remain > 0:
            borrower["owes"][lender_name] = borrower["owes"].get(lender_name, 0) + remain