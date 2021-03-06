#include "GamePrivate.h"
#include "GameApplication.h"

    GameApplication::GameApplication(QString name, int argc, char* argv[])
        : Application(name, argc, argv)
        , m_TickTimer()
    {
        connect(&m_TickTimer, SIGNAL(timeout()), this, SLOT(OnTick()));
    }

    GameApplication::~GameApplication()
    {
        SAFE_DELETE(m_pEngine);
        SAFE_DELETE(m_pRenderer);
    }

    bool GameApplication::Init()
    {
        if (!Application::Init())
        {
            return false;
        }

        if (!InitApp())
        {
            return false;
        }

        if (!InitEngine())
        {
            return false;
        }

        m_Timer.Start();

        m_TickTimer.start();
        return true;
    }

    bool GameApplication::InitApp()
    {
        return true;
    }

    bool GameApplication::InitEngine()
    {
        // Initialize renderer

        QString sRendererClassName = Application::Instance().GetSetting("Engine", "Engine/RendererClass", "D3D9Renderer").toString();

        m_pRenderer = (Renderer*)ClassFactory::CreateInstance(sRendererClassName.toAscii());
        BM_Assert(m_pRenderer != NULL);

        m_pRenderer->Init(m_pRenderWidget);

        // Initialize game engine

        QString sGameEngineClassName = Application::Instance().GetSetting("Engine", "Engine/EngineClass", "GameEngine").toString();

        m_pEngine = (GameEngine*)ClassFactory::CreateInstance(sGameEngineClassName.toAscii());
        BM_Assert(m_pEngine != NULL);

        m_pEngine->Init();

        return true;
    }

    void GameApplication::Exit()
    {
        if (m_pEngine != NULL)
        {
            m_pEngine->Exit();
        }

        if (m_pRenderer != NULL)
        {
            m_pRenderer->Exit();
        }

        Application::Exit();
    }

    void GameApplication::Tick(f32 fDeltaTime)
    {
        if (m_pEngine != NULL)
        {
            m_pEngine->Tick(fDeltaTime);
        }

        if (m_pRenderer != NULL)
        {
            m_pRenderer->Tick(fDeltaTime);
        }
    }

    void GameApplication::OnTick()
    {
        static u64 LastTicks = m_Timer.Ticks();

        u64 iTicks = m_Timer.Ticks();
        u64 iDeltaTicks = Timer::DeltaTicks(LastTicks, iTicks);
        f64 fDeltaSeconds = Timer::TicksToSeconds(iDeltaTicks);
        LastTicks = iTicks;

        Tick((f32)fDeltaSeconds);
    }
