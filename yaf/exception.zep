/**
 * Yaf Exception
 */
/**
 * @namespace
 */
namespace Yaf;

class Exception extends \Exception
{
    public static function trigger_error(errmsg = "", errtype = 0) -> void
    {
        var app;
    
        let app =  Application::app();
        
        if app != null {
            app->setErrorNo(errtype);
            app->setErrorMsg(errmsg);
        }
        trigger_error(errmsg, errtype);
    }

}