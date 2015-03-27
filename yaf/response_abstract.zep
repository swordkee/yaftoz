/**
 * Yaf_Response_Abstract
 *
 * Base class for Yaf_Controller responses
 *
 */
/**
 * @namespace
 */
namespace Yaf;

abstract class Response_Abstract
{
    /**
     * Default body name
     */
    const DEFAULT_BODY = "content";
    /**
     * Body content
     * @var array
     */
    protected _body = [];
    /**
     * Array of headers. Each header is an array with keys 'name' and 'value'
     * @var array
     */
    protected _headers = [];
    /**
     * Determine to send the headers or not
     * @var unknown_type
     */
    protected _sendheader = false;
    /**
     * Append content to the body content
     *
     * @param string $content
     * @param string $key
     * @return Yaf_Response_Abstract
     */
    public function appendBody(body, string key = NULL)
    {
        if !strlen(key) {
            let key =  self::DEFAULT_BODY;
        }
        if !isset this->_body[key] {
            let this->_body[key] = "";
        }
        let this->_body[key] .= (string) body;
        
        return this;
    }
    
    /**
     * Clear the entire body
     *
     * @param string $key
     * @return boolean
     */
    public function clearBody(string key = NULL) -> boolean
    {
        if strlen(key) {
            if array_key_exists(key, this->_body) {
                unset(this->_body[key]);
            }
        } else {
            let this->_body =  [];
        }
        return true;
    }
    
    /**
     * Clear headers
     *
     * @return Yaf_Response_Abstract
     */
    public function clearHeaders()
    {
        let this->_headers =  [];
        
        return this;
    }
    
    protected function __clone() -> void
    {
    }
    
    public function __construct() -> void
    {
    }
    
    public function __destruct() -> void
    {
    }
    
    /**
     * Return the body content
     *
     * @param string $key
     * @return string
     */
    public function getBody(string key = NULL) -> string
    {
        if !strlen(key) {
            let key =  self::DEFAULT_BODY;
        }
        return array_key_exists(key, this->_body) ? this->_body[key] : null;
    }
    
    /**
     * Return array of headers; see {@link $_headers} for format
     *
     * @return array
     */
    public function getHeader() -> array
    {
        return this->_headers;
    }
    
    /**
     * Prepend content the body
     *
     * @param string $body
     * @param string $key
     * @return Yaf_Response_Abstract
     */
    public function prependBody(string body, string key = null)
    {
        if !strlen(key) {
            let key =  self::DEFAULT_BODY;
        }
        
        if !isset this->_body[key] {
            let this->_body[key] = "";
        }
        let this->_body[key] = body . this->_body[key];
        
        return this;
    }
    
    /**
     * Send the response, including all headers
     *
     * @return void
     */
    public function response()
    {
        var body;
        
        if this->_sendheader == true {
            this->sendHeaders();
        }
        for body in this->_body {
            echo body;
        }
    }
    
    public function setAllHeaders()
    {
        return false;
    }
    
    /**
     * Set body content
     *
     * @param string $body
     * @param string $key
     * @return Yaf_Response_Abstract
     */
    public function setBody(string body, string key = NULL)
    {
        if !strlen(key) {
            let key =  self::DEFAULT_BODY;
        }
        let this->_body[key] = (string) body;
        return this;
    }

    /**
     * Set a header
     *
     * If $replace is true, replaces any headers already defined with that
     * $name.
     *
     * @param string $name
     * @param string $value
     * @param boolean $replace
     * @return Yaf_Response_Abstract
     */
    public function setHeader(name, value, replace = false)
    {
        var key, header;
    
        let name =  this->_normalizeHeader(name);
        let value =  (string) value;
        
        if replace {
            for key, header in this->_headers {
                
                if name == header["name"] {
                    unset(this->_headers[key]);
                
                }
            }
        }
        
        let this->_headers[] =  ["name" : name, "value" : value, "replace" : replace];
        
        return this;
    }
    
    /**
     * Set redirect URL
     *
     * Sets Location header. Forces replacement of any prior redirects.
     *
     * @param string $url
     * @return Yaf_Response_Abstract
     */
    public function setRedirect(string url)
    {
        this->setHeader("Location", url, true);
        return this;
    }
    
    /**
     * Magic __toString functionality
     *
     * Returns response value as string
     * using output buffering.
     *
     * @return string
     */
    public function __toString() -> string
    {
        ob_start();
        this->response();
        return ob_get_clean();
    }
    
    //method added to be possible
    /**
     * Normalize a header name
     *
     * Normalizes a header name to X-Capitalized-Names
     *
     * @param  string $name
     * @return string
     */
    protected function _normalizeHeader(name)
    {
        var filtered;
    
        let filtered =  str_replace(["-", "_"], " ", (string) name);
        let filtered =  ucwords(strtolower(filtered));
        let filtered =  str_replace(" ", "-", filtered);
        
        return filtered;
    }
    
    /**
     * Send all headers
     *
     * Sends any headers specified.
     * If an {@link setHttpResponseCode() HTTP response code}
     * has been specified, it is sent with the first header.
     *
     * @return Yaf_Response_Abstract
     */
    protected function sendHeaders()
    {
        var header;
    
        for header in this->_headers {
            header(header["name"] . ": " . header["value"], header["replace"]);
        }
        
        return this;
    }

}