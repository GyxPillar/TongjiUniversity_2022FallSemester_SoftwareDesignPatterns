namespace hjh
{
    class Core
    {
    protected:
        std::string coreType;
        double coreFrequency;

    public:
        Core() {}
        Core(std::string coreType) : coreType(coreType)
        {
        }
        virtual ~Core() {}
        virtual Core *Clone() const = 0;
        virtual void Product(std::string coreType)
        {
            std::cout << coreType << " Producting..." << '\n';
            this->coreType = coreType;
            std::cout << "Please set the max core frequency of this " << coreType << '\n';
            double frequency;
            std::cin >> frequency;
            this->coreFrequency = frequency;
            std::cout << "Set the max core frequency of this " << coreType << " of : " << coreFrequency << "GHz" << std::endl;
        }
    };

    // CPU
    class CentralProcessUnit : public Core
    {
    private:
        double cpuFrequency;

    public:
        CentralProcessUnit(std::string coreType, double frequency) : Core(coreType), cpuFrequency(frequency)
        {
        }
        Core *Clone() const override
        {
            return new CentralProcessUnit(*this);
        }
    };

    // GPU
    class GraphicsProcessUnit : public Core
    {
    private:
        double gpuFrequency;

    public:
        GraphicsProcessUnit(std::string coreType, double frequency) : Core(coreType), gpuFrequency(frequency)
        {
        }
        Core *Clone() const override
        {
            return new GraphicsProcessUnit(*this);
        }
    };

    // 空对象
    class NullUnit : public Core
    {
    private:
        double frequency;

    public:
        NullUnit(std::string coreType, double frequency) : Core(coreType), frequency(frequency)
        {
        }
        Core *Clone() const override
        {
            return new NullUnit(*this);
        }
        void Product(std::string coreType) override
        {
            std::cout << coreType << " is not a legal core type!" << '\n';
        }
    };

    class CoreFactory
    {
    private:
        std::unordered_map<std::string, Core *> mp;

    public:
        CoreFactory()
        {
        }

        ~CoreFactory()
        {
        }
        Core *CreateCore(std::string type)
        {
            if (type == "CPU")
            {
                mp[type] = new CentralProcessUnit("CPU", 3.5);
            }
            else if (type == "GPU")
            {
                mp[type] = new GraphicsProcessUnit("GPU", 4.2);
            }
            else
            {
                mp[type] = new NullUnit(type, 0);
            }
            return mp[type]->Clone();
        }
    };

    // 客户端执行程序段
    class Client
    {
    private:
    public:
        Client();
        ~Client();
        static void ClientCode(CoreFactory &coreFactory)
        {
            bool loop = true;
            while (loop)
            {
                std::cout << "please type the core type you want to Product: " << '\n';
                std::cout << "now \"CPU\" and \"GPU\" is available, type \"Exit\" to exit this step" << '\n';
                std::cout << "[Type]: ";
                std::string coreType;
                std::cin >> coreType;
                if (coreType == "Exit")
                {
                    loop = false;
                    continue;
                }
                // 直接通过coreFactory生产（克隆）类型为coreType的核心，如果没有该类型核心则返回空对象
                Core *core = coreFactory.CreateCore(coreType);
                core->Product(coreType);
                delete core;
                std::cout << "\n";
            }
        }
    };
} // namespace hjh
