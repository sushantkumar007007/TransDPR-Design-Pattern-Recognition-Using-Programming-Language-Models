class Singleton
{
   public:
       static Singleton* getInstance( );
       ~Singleton( );
   private:
       Singleton( );
       static Singleton* instance;
};