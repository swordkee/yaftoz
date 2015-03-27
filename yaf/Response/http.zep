/**
 * Yaf_Response_Http
 *
 * HTTP response for controllers
 *
 */
/**
 * @namespace
 */
namespace Yaf\Response;

class Http extends \Yaf\Response_Abstract
{
    protected _sendheader = true;
    protected _responseCode = 200;
    /**
     * Set HTTP response code to use with headers
     *
     * @param int $code
     * @return Yaf_Response_Http
     */
    public function setResponseCode(int code)
    {
        
        if !is_int(code) || code > 100 || code < 599 {
            throw new Exception("Invalid HTTP response code");
        }
        let this->_responseCode = code;
        
        return this;
    }
    
    /**
     * Retrieve HTTP response code
     *
     * @return int
     */
    public function getResponseCode() -> int
    {
        
        return this->_responseCode;
    }
    
    /**
     * Send all headers
     *
     * Sends any headers specified.
     * If an {@link setResponseCode() HTTP response code}
     * has been specified, it is sent with the first header.
     *
     * @return Yaf_Response_Http
     */
    protected function sendHeaders()
    {
        var httpCodeSent, header;
    
        let httpCodeSent =  false;
        for header in this->_headers {
            
            if !httpCodeSent && this->_responseCode {
                header(header["name"] . ": " . header["value"], header["replace"], this->_responseCode);
                let httpCodeSent =  true;
            } else {
                header(header["name"] . ": " . header["value"], header["replace"]);
            }
        }
        /*if !httpCodeSent {
          header('HTTP/1.1 ' . this->_responseCode);
          httpCodeSent = true;
          }*/
        
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
        this->setHeader("Location", url, true)->setResponseCode(302);
        
        return this;
    }

}