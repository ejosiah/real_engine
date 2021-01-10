namespace real {

    class Scene;

    class Renderer{
    public:
        virtual void init(const GraphicsContext& gContext, const Scene& scene) = 0;

        virtual void render(const Scene& scene) = 0;
    };
}