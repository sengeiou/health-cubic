#pragma once
#include <lvgl/lvgl.h>
#include "../utils.h"
#include "../Style.h"

class App;

class Page
{
private:
    lv_obj_t* root = nullptr;

public:
    Page() {}

    lv_obj_t* Root()
    {
        if (root == nullptr)
        {
            root = PageRoot();
        }
        return root;
    }

    virtual void Close()
    {
        if (root != nullptr)
        {
            lv_obj_del(root);
            root = nullptr;
        }
    }

    virtual ~Page()
    {
        Close();
    }

    virtual void Show() = 0;

    virtual void Update(int tick) {}

    virtual void Init() {}
};

