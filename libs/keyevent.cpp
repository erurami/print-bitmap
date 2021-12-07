
int getEvents(Event* pEventDes, int maxEventGet)
{

    int input_keycode;

    for (int i = 0; i < maxEventGet; i++)
    {
        if (!kbhit())
        {
            return i;
        }

        input_keycode = getch();
        Event key_event;

        switch (input_keycode)
        {
            case 1 ... 31:
                key_event.Type = 1;
                key_event.Info = input_keycode;
                pEventDes[i] = key_event;
                break;

            case 224:
                key_event.Type = 1;
                key_event.Info = getch();
                pEventDes[i] = key_event;
                break;

            default:
                key_event.Type = 0;
                key_event.Info = input_keycode;
                pEventDes[i] = key_event;
                break;
        }

    }
    return maxEventGet;
}

Event waitEvent()
{
    Event evGotEvent;

    while (!getEvents(&evGotEvent, 1))
    {
    }

    return evGotEvent;
}
