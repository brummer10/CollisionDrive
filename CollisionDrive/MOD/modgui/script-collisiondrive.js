function (event) {
    
    function set_knob_image(p) {
        if (p > 0.0001) {
            //event.icon.find ('[mod-port-symbol=GATE]').removeClass('mod-tune-blue-image').addClass('mod-tune-image');
            event.icon.find ('[mod-port-symbol=GATE]').css('background-image', 'url("/resources/knobs/boxy/tune.png?uri=https%3A//github.com/brummer10/CollisionDrive")');
        } else {
            //event.icon.find ('[mod-port-symbol=GATE]').removeClass('mod-tune-image').addClass('mod-tune-blue-image');
            event.icon.find ('[mod-port-symbol=GATE]').css('background-image', 'url("/resources/knobs/boxy/tune_blue.png?uri=https%3A//github.com/brummer10/CollisionDrive")');
        }
    }

    function handle_event (symbol, value) {
        switch (symbol) {
            case 'V1':
                set_knob_image(value);
                break;
            default:
                break;
        }
    }

    if (event.type == 'start') {
        var ports = event.ports;
        for (var p in ports) {
            handle_event (ports[p].symbol, ports[p].value);
        }
    }
    else if (event.type == 'change') {
        handle_event (event.symbol, event.value);
    }
}
