#include <iostream>
#include <stdexcept>
using namespace std;

class ShopException : public runtime_error
{
public:
    ShopException(const string& message) : runtime_error(message){}
};

class ProductNotFoundException : public ShopException
{
private:
    int productId;
public:
    ProductNotFoundException(int pId) : ShopException("Product not found"), productId(pId) {}
    
    int getProductId() const{
        return productId;
    }
};

class InsufficientStockException : public ShopException
{
private:
    int available;
    int requested;

public:
    InsufficientStockException(int available,
                               int requested)
        : ShopException("Insufficient stock"),
          available(available),
          requested(requested)
    {
    }

    int getAvailable() const
    {
        return available;
    }

    int getRequested() const
    {
        return requested;
    }
};

class PaymentFailedException : public ShopException
{
private:
    double amount;

public:
    PaymentFailedException(double amount)
        : ShopException("Payment failed"),
          amount(amount)
    {
    }

    double getAmount() const
    {
        return amount;
    }
};

int main() {
    try
    {
        throw ProductNotFoundException(15);
    }
    catch(const ProductNotFoundException& e)
    {
        cout << e.what() << '\n';
        cout << "Product ID: "
             << e.getProductId()
             << endl;
    }
    
}