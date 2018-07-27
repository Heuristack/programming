template <typename ... Types>
struct TemplateClass
{};

template <typename ... Types>
void template_function(Types ... arguments)
{}

template <typename ... Types, typename Type1>
struct KOTemplateClass
{};

template <typename ... Types, typename Type1>
void ok_template_function(Type1, Types ...)
{}

int main()
{
    TemplateClass<>             object1;
    TemplateClass<long>         object2;
    TemplateClass<long, char>   object3;

    template_function();
    template_function(1);
    template_function(1,2);
}

